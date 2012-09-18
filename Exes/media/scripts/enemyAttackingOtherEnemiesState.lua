--------------------------------------------------
--				Estado de un enemigos cuando esta a tacando a otros enemigos					--
--------------------------------------------------

-- Recogida de eventos del estado attackingOtherEnemies.
function attackingOtherEnemiesStateEvent(event, entity)
	--print("attackingOtherEnemiesStateEvent")
	local nextState
	nextState = 6
	
	
	return nextState
end

-- Acción del estado attackingOtherEnemies.
function attackingOtherEnemiesStateAction(entity)

	print("attackingOtherEnemiesStateAction")
	
	if ( enemies[entity].stopEffect) then
		--print("Second time")
		if (enemies[entity].target == nil) then
			decideAttackOtherEnemy(entity)
		end
	else
		print("ENTRAMOS AL ESTADO attackingOtherEnemiesStateAction")
		decideAttackOtherEnemy(entity)
		enemies[entity].stopEffect = 7500
	end
	
	enemies[entity].stopEffect = enemies[entity].stopEffect - enemies[entity].deltaTime
	
	local nextState
	nextState = 6
	
	if (enemies[entity].stopEffect < 0 or enemies[entity].target == nil) then
		print("SALIMOS DEL ESTADO attackingOtherEnemiesStateAction")
		enemies[entity].stopEffect = nil
		
		--Decimos que pare de atacar
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(entity)
		mensaje:send()
			
		nextState = 1
		--nextState = enemies[entity].previousState
	end
	
	return nextState
end

function decideAttackOtherEnemy(attacker)
	enemies[attacker].target = nil
	
	if (enemigosConfundidos) then
		enemies[attacker].target = nil
		for spawnID, enemyID in pairs(enemigosConfundidos) do
			--print("spawnID ", spawnID, "enemyID", enemyID, "attacker ", attacker)
			if (enemyID ~= attacker) then
				print("ENEMIGO CERCA")
				enemies[attacker].target = enemyID
			else
				print("Es el mismo")
			end
		end
		
		--enemigosConfundidos = nil
		if (enemies[attacker].target ~= nil) then
			local mensaje = LUA_MAttackEntity()
			mensaje:setAttack(true)
			mensaje:setEntity(enemies[attacker].target)
			mensaje:setEntityTo(attacker)
			mensaje:send()
		else
			local mensaje = LUA_MAttackEntity()
			mensaje:setAttack(false)
			mensaje:setEntityTo(attacker)
			mensaje:send()
		end
	else
		print("ERROR LUA (enemyAttackingOtherEnemies) deberia existir la variable enemigosConfundidos")
	end
	

end