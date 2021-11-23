library(Rmixmod)
if(!file.exists('../learnResults/res.mixmod')){
  stop("Please run example.sh first!")
}
x <- mixmodLearn(xmlIn=mixmodXmlInput('../learnResults/res.mixmod',numFormat="hexBinary", conversionOnly=TRUE))
x
