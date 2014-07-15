name = 'Bucket'
description = "A wooden bucket. It might have been able to hold water at one point, but it definitely couldn't any more."
location = 'room3:1'
obtainable = '1'
visible = '1'

function onTake()
  bucketOnHead = false;
end

function onUse(command)
  if not te:playerHasItem(name) then
    te:addMessage("You don't see anything to put in the bucket... It's probably big enough to fit over your head though.\n");
    return;
  end

  if not bucketOnHead then
    te:addMessage("There isn't much to use it on. You put it over your head, but that doesn't accomplish much.\n");
    bucketOnHead = true;
  else
    te:addMessage("You take the bucket off your head.\n");
    bucketOnHead = false; 
  end
end

function onHelp()
  te:addMessage("No special paramaters, just use it!\n");
end
