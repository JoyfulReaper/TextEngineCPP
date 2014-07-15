name = 'Bed'
description = "It's one of those fancy beds with the curtains you can pull around it. The covers are a deep red and look very expensive."
location = 'room6:1'
obtainable = '0'
visible = '0'

function onUse(command)
  te:addMessage("Do you really think you should be sleeping right now?\n");
end

function onTake()
  te:addMessage("Really? Do you really think you can carry a bed around with you?\n");
end
