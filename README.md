# GameEngines

Project code for 4th year game engines class at Champlain College

See [This Video](Project%201%20Vid.mp4) for a video of this module working in engine. 

Use the following code inside GoDot after creating a FollowMouseNode to test this project: 


```python
extends FollowMouseNode


func _ready():
	print("It's Alive!")
	var mousePos = get_viewport().get_mouse_position();
	setLocation(mousePos.x,mousePos.y)
	if loadImage("icon.png") > 0:
		print("Error loading image")

func _input(event):
   if event is InputEventMouseMotion:
	   setLocation(event.position.x, event.position.y)
```
PS. All this code was written by me AmeliaRose802. I have no idea why the commits are showing at @WaterBaby15. That is an old account I made in 9th grade and I didn't even know it still existed. How it ended up being the credentals on my brand new computer is a mystery for the ages
