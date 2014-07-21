name = 'Armor'
description = "A suit of armor on a stand"
location = 'room1:1'
obtainable = '0'
visible = '0'

function onUse(command)
  te:addMessage("You try to put it on, but it's too big. You decide to put it back.\n");
end

function onTake()
  te:addMessage("You can take the armor apart, but it's way too heavy to carry around.\n");
end
