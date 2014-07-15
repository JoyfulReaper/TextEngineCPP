name = 'South Window'
description = "You look out the window. A dark forest stretches out as far as you can see."
location = 'room6:1'
obtainable = '0'
visible = '1'

function onUse(command)
  te:addMessage(description .. "\n");
end

