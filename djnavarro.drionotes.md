## Notes on djnavarros paper

### Barnsley Fen

```
f(x,y) = [a b] [x] + [e]
         [c d] [y]   [f]
```

The key properties of affine transformations are that they:

1. Preserve straight lines (lines stay lines)
2. Preserve ratios of distances along any single line
3. Preserve parallelism
4. Can combine rotation, scaling, shearing, and translation

But there is so much more:

1. Predictable Yet Complex Behavior

Each affine transformation does something simple and predictable (like rotate,
scale, or shift), but when you apply them repeatedly in an iterated function
system, you get incredibly complex and beautiful patterns. In the Barnsley fern
example, there are four transformation functions: one makes the stem, one makes
ever-smaller leaflets, and two make the largest left and right leaflets Art
from code V: Iterated function systems – Notes from a data witch.

2. Computational Efficiency

Matrix operations are fast! Instead of complex trigonometric calculations or
other expensive operations, you're just doing matrix multiplication and
addition. 

3. Compositional Nature

You can combine multiple affine transformations by multiplying their matrices
together. This means you can build complex transformations from simple building
blocks.

4. Fractal generation

When used in iterated function systems, affine transformations naturally create
fractals. The chaos game works by repeatedly applying randomly chosen
transformations to generate points that converge to a fractal shape

5. Art control:

a and d control scaling
b and c control shearing/rotation
e and f control translation

#### The contribution of each function

Looking at the Barnsley fern coefficients from the article:

f₁ (stem): Mostly just scales y by 0.16 - creates the vertical stem
f₂ (main structure): Scales and slightly rotates - creates the repetitive leaflet pattern
f₃ and f₄ (large leaflets): Create the distinctive left and right fronds

When you color-code which transformation created each point, you can see
exactly how each function contributes to the final shape.

(Important for debugging).

#### Applying the transform functions

But notice the probabilities aren't equal:

f₁ (stem): 1% chance - rarely chosen
f₂ (main leaflets): 85% chance - chosen most often
f₃ (left leaflet): 7% chance
f₄ (right leaflet): 7% chance

### Happy accidents

#### Chaos game for unboxing

The structure of the algorithm is the same as the Barnsley fern chaos game.

#### Algorithm

We have:

AM: affine matrices
    - A_i: afffine transformation matrices (layers)
VF: variant functions
    - g_j = variant functions

The affine transformation coefficents have been sampled at random.
We have 3 variant functions: two   sinusoidal and one rescaling.
ponts are in 3d: (x,y,z); z is color.


1. Start with a point
2. Sample a AM and VF
3. Apply the transformation f_ij = g_j(A_i * x)
4. Repeat with new point

In more detail:

1. Setup Phase

- Choose number of layers (affine transformations)
- Generate random coefficients for each layer
- Define variant functions
- Set starting point (x₀, y₀, z₀)

2. Coefficient Generation

The coefficients are stored in an array: coeffs[,,i] is the matrix of
coefficients A_i, with values "sampled uniformly at random, with values ranging
from -1 to 1".

Each layer gets a 3×3 matrix of random coefficients:

```
A_i = [a b e]  <- coefficients for x transformation
      [c d f]  <- coefficients for y transformation  
      [g h k]  <- coefficients for z transformation
```

They are: "sampled uniformly at random, with values ranging from -1 to 1".


3. Variant Functions

There are "three variant functions g_j in this system".

g₁ (rescaling): point + (sum(point²))^(1/3) - shifts points toward top-right
g₂ (sine wave): sin(point) - creates wavy, bounded patterns
g₃ (double sine): 2 * sin(point) - creates larger wavy patterns

4. Iteration Loop

For each iteration:

Randomly pick a layer (1 to number of layers)
Randomly pick a variant function (1 to 3)
Apply affine transformation:
new_point = A_layer × current_point

Apply variant function:

final_point = g_function(new_point)

Special color handling: "the weirdness with point[3] is me treating colour as
special" - the z-coordinate gets blended: point[3] = (point[3] + z)/2

#### The "Unboxing" Pattern

The outputs "have a fairly consistent look and feel: a pair of nested boxes,
with something 'bursting' from the top right corner".

Boxes come from: Sine functions constraining coordinates to [-1,1] ranges

Bursting effect comes from: The rescaling function pushing points outward

Nested structure comes from: Multiple affine layers creating scaled/rotated

versions Fine details come from: Random interplay between all components

#### The magic (key insight)

Affine transformations handle geometric distortions (rotation, scaling, shearing)

Variant functions handle mathematical "flavoring" (waves, rescaling, etc.)

Random sampling of both creates emergent complexity

### Regarding color

The z-coordinate gets mapped to a color gradient, not grayscale. Let me check
what the article says about color handling:

From the article, the z-coordinate gets special treatment - there's "weirdness
with point[3] is me treating colour as special" and they blend it: point[3] =
(point[3] + z)/2.

Also, they use color palettes like:
sample_canva2 <- function(seed = NULL, n = 4) {
  sample(ggthemes::canva_palettes, 1)[[1]] |>
    (\(x) colorRampPalette(x)(n))()
}

So instead of grayscale, we should:

1. Map z-values to a color palette (like red → orange → yellow → white)
2. Handle the z-blending properly in our variant functions

