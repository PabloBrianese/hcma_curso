gif_left=./fourierSeriesSolution/dat/fourierSeriesSolution.gif
gif_right=./OpenFOAMSolution/dat/OpenFOAMSolution.gif

convert $gif_left -repage 1200x640 -coalesce \
          null: \( $gif_right -coalesce \) \
          -geometry +600+0 -layers Composite comparison.gif
