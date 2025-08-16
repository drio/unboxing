library(tibble)
library(ggplot2)
library(ggthemes)

unbox_art <- function(data, seed = NULL, size = 1) {
  
  # convert to data frame and sample a palette
  data <- data |> as.data.frame() |> as_tibble()
  names(data) <- c("x", "y", "c", "l", "t")[1:ncol(data)]
  shades <- sample_canva2(seed)
  
  # render image as a scatter plot
  ggplot(data, aes(x, y, colour = c)) +
    geom_point(
      size = size,
      stroke = 0,
      show.legend = FALSE
    ) + 
    theme_void() + 
    coord_equal(xlim = c(-4, 4), ylim = c(-4, 4)) + 
    scale_colour_gradientn(colours = shades) + 
    scale_x_continuous(expand = c(0, 0)) +
    scale_y_continuous(expand = c(0, 0)) +
    theme(panel.background = element_rect(
      fill = shades[1], colour = shades[1]
    ))
}

sample_canva2 <- function(seed = NULL, n = 4) {
  if(!is.null(seed)) set.seed(seed)
  sample(ggthemes::canva_palettes, 1)[[1]] |>
    (\(x) colorRampPalette(x)(n))()  
}

unboxer_base <- function(iterations, layers, seed = NULL) {
  if(!is.null(seed)) set.seed(seed)
  
  # coefficients defining affine layer transforms, A_i
  coeffs <- array(
    data = runif(9 * layers, min = -1, max = 1), 
    dim = c(3, 3, layers)
  )
  
  # list of variant functions, g_j
  funs <- list(
    function(point) point + (sum(point ^ 2)) ^ (1/3),
    function(point) sin(point),
    function(point) 2 * sin(point)
  )
  
  # updater function: apply the layer, then the function
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
  
  points <- vector("list", iterations + 1)
  points[[1]] <- point0  # Changed from 'point' to 'point0'
  
  for(i in 1:iterations) {
    points[[i + 1]] <- update(points[[i]], layer_ind[i], trans_ind[i])
  }
  
  # Convert list to matrix first
  points_matrix <- do.call(rbind, points)
  
  # Then add columns and return
  points <- cbind(
    points_matrix,
    c(0, layer_ind),
    c(0, trans_ind)
  )
  return(points)
}

#print(unboxer_base(10, layers = 1, seed = 333))

#tic()
unboxer_base(1000000, layers = 3, seed = 66) |> 
  unbox_art(seed = 66, size = .1)
