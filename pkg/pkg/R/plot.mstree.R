"plot.mstree" <-
function(mst,x,segcol=1,add=FALSE){
  require(multiv)
  dt<-pca(x)$rproj[,1:2]
  if(add)points(dt[,1],dt[,2])
  else plot(dt[,1],dt[,2])
  segments(dt[mst$mst[,1],1],dt[mst$mst[,1],2],
           dt[mst$mst[,2],1],dt[mst$mst[,2],2],col=segcol)

}
