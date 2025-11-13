from manim import *

class RotScene2D(Scene):
	def construct(self):
		# Coordinate system
		x_range = [-10, 10, 1]
		y_range = [-5, 5, 1]
		x_length = 10
		y_length = 5

		grid = NumberPlane(
			x_range=x_range,
			y_range=y_range,
			x_length=2 * x_length,
			y_length=2 * y_length,
			background_line_style={"stroke_opacity": 0.3}
		).move_to(ORIGIN)

		axes = Axes(
			x_range=x_range,
			y_range=y_range,
			x_length=2 * x_length,
			y_length=2 * y_length,
			axis_config={"color": WHITE},
		).move_to(ORIGIN)

		x_label = axes.get_x_axis_label(Tex("x"))
		y_label = axes.get_y_axis_label(Tex("y"))

		# animate
		self.play(Create(grid))
		self.play(Create(axes))
		self.play(Write(x_label), Write(y_label))
		self.wait(1)

		x0, y0 = 2, 0
		point_pos_x = Vector(axes.coords_to_point(x0, y0), color=YELLOW)
		self.play(FadeIn(point_pos_x))
		self.wait(0.5)

		label_start = MathTex(r"(2,\ 0)").next_to(axes.coords_to_point(x0, y0), UP)
		self.play(FadeIn(label_start))
		self.wait(0.5)

		import numpy as np
		theta = np.radians(30)
		x1 = x0 * np.cos(theta) - y0 * np.sin(theta)
		y1 = x0 * np.sin(theta) + y0 * np.cos(theta)

		self.play(
			point_pos_x.animate.put_start_and_end_on(
				axes.coords_to_point(0, 0), axes.coords_to_point(x1, y1)
			),
			run_time=2
		)

		tip_pos_x = axes.coords_to_point(x1, y1)
		dot = Dot(tip_pos_x, color=YELLOW)
		self.play(FadeIn(dot), FadeOut(point_pos_x))
		self.wait(1)

