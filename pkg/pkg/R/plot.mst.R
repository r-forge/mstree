"plot.mst" <-
function(mst,x,segcol=1,add=FALSE){
  require(multiv)
  dt<-pca(x)$rproj[,1:2]
  if(add)points(dt)
  else plot(dt)
  segments(dt[mst$mst[,1],1],dt[mst$mst[,1],2],
           dt[mst$mst[,2],1],dt[mst$mst[,2],2],col=segcol)

}
