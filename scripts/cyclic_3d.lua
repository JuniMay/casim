name        = "Cyclic 3D"
state_count = 16
color       = { 
    "#000000", "#ff44aa", "#ff3333", "#ff7744", 
    "#ffaa33", "#ffcc22", "#ffff33", "#ccff33", 
    "#99ff33", "#33ff33", "#33ffaa", "#33ffdd", 
    "#33ffff", "#33ccff", "#5599ff", "#5555ff",
}
dimensions  = 3
min_size    = { 35, 35, 35 }

function local_evolve(x)
    sum = 0
    for i = 1, 13 do
        if (x[i] == x[14] + 1) then
            sum = sum + 1
        end
    end
    for i = 15, 27 do
        if (x[i] == x[14] + 1) then
            sum = sum + 1
        end
    end
    if (x[14] <= state_count - 2 and sum >= 2) then
        return x[14] + 1
    elseif (x[14] == state_count - 1) then
        return 0
    end
    return x[14]
end
