--------------------------------------------------
--				Estado idle						--
--------------------------------------------------

function godBuildingSelectionEvent(target, point_x, point_y, point_z)
	print("Selectado - construido")
	emplaceBuild()
	return 2
end

function godBuildingActionEvent(target, point_x, point_y, point_z)
	print("Actuado - construido")
	
	return 2
end

function setBuildingState()
	print("set building state")
	God.currentState = 2
end

function finishBuildingState()
	God.currentState = 1
end