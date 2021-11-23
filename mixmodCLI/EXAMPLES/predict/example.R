library(Rmixmod)
if(!file.exists('../predictResults/res.mixmod')){
  stop("Please run example.sh first!")
}
x <- mixmodPredict(xmlIn=mixmodXmlInput('../predictResults/res.mixmod',numFormat="hexBinary", conversionOnly=TRUE))
x
