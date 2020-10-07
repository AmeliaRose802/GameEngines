# GameEngines

ECS Game of Pong. Most functionality handled by the C++. Process not being called for some reason so you must add an ecs node to the scene and add a script with the following to make the project work. The game must load a number of packed scenes to work so for best results download and run the included zipped game file.


func _process(delta):
	updateSystems(delta)
