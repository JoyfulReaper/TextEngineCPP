name = 'West Window'
description = "You look out the window. There's a wide river flowing South, then bending away to the West."
location = 'room6:1'
obtainable = '0'
visible = '1'

function onUse(command)
  te:addMessage(description .. "\n");
end

