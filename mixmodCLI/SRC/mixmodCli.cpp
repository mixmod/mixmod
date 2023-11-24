#include <getopt.h>
#include <iostream>
#include <mixmod.h>
#include <mixmod_iostream/IOStreamUtil.h>
#include <string>

using namespace std;

// print program usage
void showTestsHelp()
{
	cout << "Usage: './mixmod-cli -m {c|l|p} -i <xml-file-in> -o <dirOut/prefix> [optional args] '." << endl;
	cout << "Usage: './mixmod-cli -m {c|l|p} -i <xml-file-in> -t [optional args] '." << endl;
	cout << "MANDATORY ARGS:" << endl;
	cout << "-m, --mode : should be 'c' (as clustering), 'l' (as learn) or 'p' (as predict)" << endl;
	cout << "-i, --in : an input XML file" << endl;
	cout << "-o, --out : <dirOut/prefix> dirOut is an existing dir, all output files generated in dirOut will start with "
	        "'prefix'"
	     << endl;
	cout << "-t, --test : when set, the input XML file is interpreted as a regresion test (i.e. input parameter+reference "
	        "result). In this case -o become optional"
	     << endl;
	cout << "OPTIONAL ARGS:" << endl;
	cout << "-b, --binaryIn : when set, float values in the input XML file are interpreted as 'hex binary' (in order to avoid "
	        "precision loss). When not set, the format is 'human readable'"
	     << endl;
	cout << "-B, --binaryOut : when set,  output float values are generated as 'hex binary' (in order to avoid precision "
	        "loss). When not set, it follows -b"
	     << endl;
	cout << "-s, --seed : integer >=0, allows to set a deterministic seed (random seed when -s is missing)" << endl;
	cout << "-h, --help : displays this help" << endl;
}

// Run test named after argv[2]; argv[1] indicates the test mode:
//   "c" for clustering, or
//   "da" for discriminant analysis

// Tests are looked for in ../DATA/, assuming we run the executable from BIN/.
// File structure: DATA/dataset/{Clustering,DiscriminantAnalysis}/{case1,...,caseN}/<p_files>,
// where <p_files> stands for "all mixmod project files" (.mxp,.mixmod...etc).

// A test run proceeds as follow:
//   1] Build input object following current mode + case parameters.
//   2] Run mixmod clustering or DA analysis.
//   3] Compare output to the expected output also contained in case[k]/...

int main(int argc, char **argv)
{

	int opt;
	int massiccc = 0;
	const char *short_opt = "m:i:bo:Bts:n:";
	struct option long_opt[] = {{"help", no_argument, NULL, 'h'},
	                            {"mode", required_argument, NULL, 'm'},
	                            {"in", required_argument, NULL, 'i'},
	                            {"out", required_argument, NULL, 'o'},
	                            {"binaryIn", no_argument, NULL, 'b'},
	                            {"BinaryOut", no_argument, NULL, 'B'},
	                            {"test", no_argument, NULL, 't'},
	                            {"seed", required_argument, NULL, 's'},
	                            {"massiccc", no_argument, NULL, 'M'},
	                            {"relpath", no_argument, NULL, 'r'},
	                            {NULL, 0, NULL, 0}};

	string mode;
	string datasetIn;
	string datasetOut;
	XEM::IoMode ioModeIn = XEM::IoMode::NUMERIC;
	XEM::IoMode ioModeOut = XEM::IoMode::NUMERIC;
	XEM::PathMode pathMode = XEM::PathMode::ABSOLUTE;
	bool nrTest = false;
	int seed = -1;
	while ((opt = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
		switch (opt) {
		case -1: /* no more arguments */
		case 0:  /* long options toggles */
			break;

		case 'm':
			mode = optarg;
			break;
		case 'i':
			datasetIn = optarg;
			break;
		case 'o':
			datasetOut = optarg;
			break;
		case 'b':
			ioModeIn = XEM::IoMode::BINARY;
			break;
		case 'B':
			ioModeOut = XEM::IoMode::BINARY;
			break;
		case 't':
			nrTest = true;
#ifdef _OPENMP
			omp_set_num_threads(1); // Force only 1 threads for non-regression tests
#endif
			break;
		case 's':
			seed = atoi(optarg);
			if (seed < 0) {
				cerr << opt << "seed must be >= 0" << endl;
				return (-2);
			}
			break;
		case 'M':
			massiccc = 1;
			break;
		case 'r':
			pathMode = XEM::PathMode::RELATIVE;
			break;
		case ':':
		case '?':
		case 'h':
			showTestsHelp();
			return (0);

		default:
			cerr << opt << "invalid option" << endl;
			return (-2);
		};
	};
	if (!mode.empty()) {
		cerr << "mode argument is obsolete, it isn't necessary anymore!" << endl;
		return 1;
	}

	/*
	if(mode.empty()){
	  cerr<<"mode argument is mandatory" <<endl;
	  return 1;
	}
	if(mode!="C" && mode!="L" && mode!="P" && mode!="c" && mode!="l" && mode!="p"){
	  cerr<<"invalid mode (should be C[lustering], L[earn] or P[redict])" <<endl;
	  return 1;
	  }*/
	if (datasetIn.empty()) {
		cerr << "the input dataset is mandatory" << endl;
		return 1;
	}
	if (datasetOut.empty() && ioModeOut == XEM::IoMode::BINARY) {
		cerr << "-B (binaryOutput) option is invalid when an output dataset is not provided" << endl;
		return 1;
	}
	if (datasetOut.empty() && !nrTest) {
		cerr << "-Out is mandatory unless -t[est] is set" << endl;
		return 1;
	}
	if (ioModeOut == XEM::IoMode::NUMERIC) {
		ioModeOut = ioModeIn; // when -B is not set, ioModeOut follows ioModeIn
	}

	// switch (mode[0]) {
	switch (XEM::getProjectType(datasetIn)) {
		// case 'c':
		// case 'C':
	case XEM::ProjectType::Clustering: {
		// Clustering mode

		// build full path mixmod file
		// string mixmodFile = string("../DATA/") + datasetName + string("/Clustering/") + testName; //old way
		// string mixmodFile = datasetIn + string("/" + datasetIn + ".mixmod");

		// build ClusteringMain object == reference output (TODO: separate input/output)
		XEM::ClusteringMain *clusteringMain = XEM::IStream_XML_Clustering(datasetIn, !nrTest, ioModeIn);

		XEM::ClusteringOutput *cRefOutput = nullptr;
		if (nrTest) {
			cRefOutput = clusteringMain->getOutput()->clone();
		}
		// run clustering (0 => antiRandomize, IoMode::BINARY => hexadecimal output for NR-tests)
		seed = seed >= 0 ? seed : (nrTest ? 0 : seed);
		clusteringMain->run(seed, ioModeIn, 0, massiccc);

		if (!datasetOut.empty()) {
			XEM::OStream_XML(datasetOut, clusteringMain, ioModeOut, pathMode);
		}

		if (nrTest) {
			// get new output, and compare to reference output [TODO: improve console output]
			XEM::ClusteringOutput *cOutput = clusteringMain->getOutput();
			if (*cOutput == *cRefOutput) {
				cout << "Everything is fine for " << datasetIn << endl;
			} else {
				cout << "Unexpected output in " << datasetIn << endl;
				return 1;
			}
			delete cRefOutput;
		}
		delete clusteringMain;

		break;
	}

		// case 'l':
		// case 'L':
	case XEM::ProjectType::Learn: {
		XEM::LearnMain *learnMain = XEM::IStream_XML_Learn(datasetIn, !nrTest, ioModeIn);

		XEM::LearnOutput *lRefOutput = nullptr;
		if (nrTest) {
			lRefOutput = learnMain->getLearnOutput(); // TODO: ->clone();
		}
		// run clustering (0 => antiRandomize, IoMode::BINARY => hexadecimal output for NR-tests)
		seed = seed >= 0 ? seed : (nrTest ? 0 : seed);
		learnMain->run(seed, ioModeIn, 0, massiccc);

		if (!datasetOut.empty()) {
			XEM::OStream_XML(datasetOut, learnMain, ioModeOut, pathMode);
		}

		if (nrTest) {
			// get new output, and compare to reference output [TODO: improve console output]
			XEM::LearnOutput *lOutput = learnMain->getLearnOutput();
			if (*lOutput == *lRefOutput) {
				cout << "Everything is fine for " << datasetIn << endl;
			} else {
				cout << "Unexpected output in " << datasetIn << endl;
				return 1;
			}
			delete lRefOutput;
		}
		delete learnMain;

		break;
	}
		// case 'p':
		// case 'P':
	case XEM::ProjectType::Predict: {
		XEM::PredictMain *predictMain = XEM::IStream_XML_Predict(datasetIn, !nrTest, ioModeIn);

		XEM::PredictOutput *pRefOutput = nullptr;
		if (nrTest) {
			pRefOutput = predictMain->getPredictOutput(); // TODO: ->clone();
		}
		// run clustering (0 => antiRandomize, IoMode::BINARY => hexadecimal output for NR-tests)
		predictMain->run(ioModeIn, 0, massiccc);

		if (!datasetOut.empty()) {
			XEM::OStream_XML(datasetOut, predictMain, ioModeOut, pathMode);
		}

		if (nrTest) {
			// get new output, and compare to reference output [TODO: improve console output]
			XEM::PredictOutput *pOutput = predictMain->getPredictOutput();
			if (*pOutput == *pRefOutput) {
				cout << "Everything is fine for " << datasetIn << endl;
			} else {
				cout << "Unexpected output in " << datasetIn << endl;
				return 1;
			}
			delete pRefOutput;
		}
		delete predictMain;

		break;
	}
	case XEM::ProjectType::Unknown:
		cerr << "Unknown project type" << endl;
		return 1;

	} // end switch

	return 0;
}
