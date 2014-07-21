name = 'Boarded Window'
description = "The window has been boarded up."
location = 'room4:1:room8:1'
obtainable = '0'
visible = '0'

function onUse(command)
  te:addMessage("You try to remove the boards, but they're stuck on there with glue or something.\n");
end

