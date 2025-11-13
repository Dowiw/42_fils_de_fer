from manim import *

# Bresenham Line
class BresenhamLineScene(Scene):
	def construct(self):
		# Define start and end points
		start = np.array([-4, -2, 0])
		end = np.array([4, 2, 0])

		# Draw grid
		grid = NumberPlane(
			x_range=[-5, 5, 1],
			y_range=[-3, 3, 1],
			background_line_style={"stroke_opacity": 0.4}
		)
		self.add(grid)

		# Bresenham's algorithm (integer grid steps)
		x0, y0 = int(start[0]), int(start[1])
		x1, y1 = int(end[0]), int(end[1])

		dx = abs(x1 - x0)
		dy = abs(y1 - y0)
		x, y = x0, y0
		sx = 1 if x0 < x1 else -1
		sy = 1 if y0 < y1 else -1

		points = []
		if dx > dy:
			err = dx / 2.0
			while x != x1:
				points.append([x, y, 0])
				err -= dy
				if err < 0:
					y += sy
					err += dx
				x += sx
			points.append([x1, y1, 0])
		else:
			err = dy / 2.0
			while y != y1:
				points.append([x, y, 0])
				err -= dx
				if err < 0:
					x += sx
					err += dy
				y += sy
			points.append([x1, y1, 0])

		# Animate filling blocks left to right
		squares = []
		for pt in points:
			sq = Square(side_length=1, color=RED, fill_opacity=0.7).move_to(pt)
			squares.append(sq)

		for sq in squares:
			self.play(FadeIn(sq), run_time=0.2)
			self.wait(0.1)
