from manim import *

# display long intro
class Intro(Scene):
		def construct(self):
			self.play(Write(Text("Hello World!")))

# diplay list of strings
class ListToLearn(Scene):
	def construct(self):
		s1 = "Render 3D points into 2D pixel values with perspective. (Rotation Matrices)"
		s2 = "Bresenham's Line Algorithm"
		s3 = "Color interpolation"
		blist = BulletedList(s1, s2, s3, height=10, width=10)
		blist.to_edge(LEFT)
		for item in blist:
			self.play(Write(item))
		self.wait(1)
		self.play(FadeOut(blist))
