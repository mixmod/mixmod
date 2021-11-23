library(Rmixmod)
if(!file.exists('../clusteringResults/res.mixmod')){
  stop("Please run example.sh first!")
}
x <- mixmodCluster(xmlIn=mixmodXmlInput('../clusteringResults/res.mixmod',numFormat="hexBinary", conversionOnly=TRUE))
x
