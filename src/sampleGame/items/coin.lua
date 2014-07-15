name = 'Coin'
description = "A dull bronze coin"
location = 'room1:1'
obtainable = '1'
visible = '1'

function onUse(command)
  if te:playerHasItem(name) then
    te:playerRemoveItem(name, 1);
  else
    te:roomRemoveItem(name, 1, te:getCharacterLocation("player"));
  end
  te:addMessage("Shiny! Kinda anyway\n");
  te:setPlayerMoney(te:getPlayerMoney() + 1);
end

function onHelp()
  te:addMessage("I don't think it's worth that much...\n");
end
