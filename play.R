unboxer_base <- function(iterations, layers, seed = NULL) {
  
  if(!is.null(seed)) set.seed(seed)
  
  # coefficients defining affine layer transforms, A_i
  coeffs <- array(
    data = runif(9 * layers, min = -1, max = 1), 
    dim = c(3, 3, layers)
  )
  #print(coeffs)
  
  # list of variant functions, g_j
  funs <- list(
    function(point) point + (sum(point ^ 2)) ^ (1/3),
    function(point) sin(point),
    function(point) 2 * sin(point)
  )
  
  # updater function: apply the layer, then the function
  # (the weirdness with point[3] is me treating colour as special)
  update <- function(point, layer, transform) {
    f <- funs[[transform]]
    z <- point[3]
    point[3] <- 1
    point <- f(point %*% coeffs[,,layer])
    point[3] <- (point[3] + z)/2
    return(point)
  }
  
  # initial point
  point0 <- matrix(
    data = runif(3, min = -1, max = 1), 
    nrow = 1,
    ncol = 3
  )
  
  # sample points
  layer_ind <- sample(layers, iterations, replace = TRUE)  
  trans_ind <- sample(length(funs), iterations, replace = TRUE)  
  points <- accumulate2(layer_ind, trans_ind, update, .init = point0)
  
  # tidy up, add columns, and return
  # points <- cbind(
  #   points,
  #   c(0, layer_ind),
  #   c(0, trans_ind)
  # )
  #return(points)
}

unboxer_base(10, layers = 1, seed = 333)
