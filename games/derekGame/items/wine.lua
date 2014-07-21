name = 'Wine'
description = "An expensive merlot."
location = "room6:1"
obtainable = '1'
visible = '1'

function onUse(command)
  if te:playerHasItem("Wine") then
    te:playerRemoveItem("Wine", 1);
  else
    te:roomRemoveItem("Wine", 1, te:getCharacterLocation("player"));
  end
  te:addMessage("You down the whole bottle in a few gulps. You really should stop drinking so much...\n");
  te:setPlayerHealth(te:getPlayerHealth() + 20);
end
