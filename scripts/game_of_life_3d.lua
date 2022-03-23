name        = "Game of Life 3D"
state_count = 2
color       = { "#000000", "#ffffff" }
dimensions  = 3
min_size    = { 30, 30, 30 }

function local_evolve(x)
    sum = 0
    for i = 1, 27 do
        sum = sum + x[i]
    end
    if (x[14] == 1) then 
        sum = sum - 1
    end
    if (x[14] == 1) then
        if (sum == 2 or sum == 3) then
            return 1
        end
    else
        if (sum == 3) then
            return 1
        end
    end
    return 0
end
