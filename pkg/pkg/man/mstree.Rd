\name{mstree}
\alias{mstree}
\title{Minnimum Spanning Tree}
\description{
Calculates a minnimum spanning tree on a matrix based on Euclidean
distance or a minnimum spanning tree on either a matrix of distances or
an object of class distance for any arbitrary distince metric
}
\usage{
mstree(x,adj=NULL,plane=FALSE,alg=2,wts=FALSE,lp=2)
}

\arguments{
  \item{x}{matrix of data where rows correspond to observations, columns
    to variables, or an nxn, symetric matrix of distances}
  \item{adj}{An adjacency list of class nb}
  \item{plane}{For compatibility with Splus, Not implemented yet}
  \item{alg}{an integer either, 1,2, or 3 to specify which algorithm to use}
  \item{wts}{a logical variable indicating whether the object being
             passed is a matrix of weights or data. Ignored if object is
	     of class dist}
  \item{lp}{The exponent for the lp distance, default=2 which is the
    Euclidean metric}
}
\details{
   A tree in graph theory is a set of n points and n-1 edges (lines)
   connecting points such that there is a path along edges between any
   given points with no cycles. A minimal spanning tree is a tree that
   has the minimal sum of the lengths of the edges. Such trees are
   useful in a variety of situations.
}
\value{

  \item{comp1 }{Description of `comp1'}
  \item{comp2 }{Description of `comp2'}

}
\references{
   Benjamin Pfaff. Uniformity testing library
   http://www.msu.edu/user/pfaffben/uniformity/uniformity.txt

   Bentley, J. L., and J. H. Friedman (1984). Fast Algorithms for Constructing
   Minimal Spanning Trees in Coordinate Spaces. IEEE Trans. on Comp.
   2, pp. 97-105. 

   Friedman, J. H. and Rafsky, L. C. (1981). Graphics for the
   Multivariate Two-Sample Problem. Journal of the American Statistical
   Association 76, 277-287.

\author{Nicholas Lewin-Koh <kohnicho@comp.nus.edu.sg>}
\note{}
\seealso{ ~~objects to SEE ALSO as \code{\link{~~fun~~}}, ~~~ }

\examples{
x<-matrix(c(rnorm(100),rnorm(100,2,1)),20,10,byrow=TRUE)
mst<-mstree(x)
dt<-plot.mstree(mst,x)
points(dt[1:10,],pch=20,col=2)
points(dt[11:20,],pch=16,col=3)
require(mva)
mst<-mstree(dist(x,method='man'))
}
\keyword{ ~kwd1 }% at least one, from doc/KEYWORDS
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
