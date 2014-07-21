name = 'Mr NPC2'
description = [[He looks mean!]]
location = 'room2'
health = 100
money = 100
canBeKilled = 1
respawnProbablity = 10

function onSay(what)
  te:addMessage("Screw your " .. what .. "\n");
end

function playerEntered()
  te:addMessage("Mr NPC2: GO AWAY!\n\n");
end

function onAttack()
  te:addMessage("Ouch! That's not very nice!");
end