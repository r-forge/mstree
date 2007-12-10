"mstree" <-
function(x,adj=NULL,plane=FALSE,alg=2,wts=FALSE,Lp=2){

    if (!is.numeric(x)) stop("Data non-numeric")
    if (any(is.na(x))) stop("Data includes NAs")
    if(is.null(adj)){
      if (!is.matrix(x) && !inherits(x,"dist"))
        stop("Data not in matrix form")
      if(inherits(x,"dist")){
        x<-as.matrix(x)
        alg<-3
      }
      if(wts){
        alg<-3
      }
      np <- nrow(x)
      dimension <- ncol(x)
      #mst<-rep(-1,2*(np-1))
      mst<-rep(-1,np)
      e.length<-rep(0,np-1)
      xx <- x[1,]
      for (i in 2:np) xx <- c(xx, x[i,])
      z <- .C("mstree", np=as.integer(np), dimension=as.integer(dimension),
              alg=as.integer(alg), xx=as.double(xx),
              mst=as.integer(mst),e.length= as.double(e.length),NAOK=TRUE)
      #res <- list(np=np, dimension=dimension,
                  #mst=matrix(z$mst,np-1,2,byrow=FALSE), weight=z$e.length)
      res <- list(np=np, dimension=dimension, mst=z$mst,
                  weight=z$e.length)
    }
    else{
      if(inherits(adj,"nb")){
        k <- unlist(lapply(adj,length))
        to <- unlist(adj)
        from <- NULL        
        for(i in 1:length(adj))from <- c(from,rep(i,k[i]))
      }
      else{
        stop("Not done yet")
      }
      np <- nrow(x)
      dimension <- ncol(x)
      mst<-rep(-1,2*(np-1))
      e.length<-rep(0,np-1)
      xx <- x[1,]
      for (i in 2:np) xx <- c(xx, x[i,])


      
      z <- .C("mstree_krusk",
              np=as.integer(np), dimension=as.integer(dimension),
              alg=as.integer(alg), xx=as.double(xx),
              mst=as.integer(mst),nE=as.integer(length(to)),
              to=as.integer(to), from=as.integer(from),
              pind=as.integer(0:(length(to)-1)),
              e.length= as.double(e.length),NAOK=TRUE)

      res <- list(np=np, dimension=dimension,
                  mst=matrix(z$mst,np-1,2,byrow=FALSE), weight=z$e.length)      

    }
    #mst=z$mst
    class(res) <- "mstree"
    attr(res, "call") <- match.call()
    invisible(res)
}
