\name{plot.mst}
\alias{plot.mst}
%- Also NEED an `\alias' for EACH other topic documented here.
\title{ ~~function to do ... ~~ }
\description{
  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
plot.mst(mst, x, segcol=1, add=FALSE)
}
%- maybe also `usage' for other objects documented here.
\arguments{
  \item{mst}{ ~~Describe \code{mst} here~~ }
  \item{x}{ ~~Describe \code{x} here~~ }
  \item{segcol}{ ~~Describe \code{segcol} here~~ }
  \item{add}{ ~~Describe \code{add} here~~ }
}
\details{
  ~~ If necessary, more details than the __description__  above ~~
}
\value{
  ~Describe the value returned
  If it is a LIST, use
  \item{comp1 }{Description of `comp1'}
  \item{comp2 }{Description of `comp2'}
  ...
}
\references{ ~put references to the literature/web site here ~ }
\author{ ~~who you are~~ }
\note{ ~~further notes~~ }

 ~Make other sections like WARNING with \section{WARNING }{....} ~

\seealso{ ~~objects to SEE ALSO as \code{\link{~~fun~~}}, ~~~ }

\examples{
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	     or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(mst,x,segcol=1,add=FALSE){
  require(multiv)
  dt<-pca(x)$rproj[,1:2]
  if(add)points(dt)
  else plot(dt)
  segments(dt[mst$mst[,1],1],dt[mst$mst[,1],2],
           dt[mst$mst[,2],1],dt[mst$mst[,2],2],col=segcol)

  }
}
\keyword{ ~kwd1 }% at least one, from doc/KEYWORDS
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
