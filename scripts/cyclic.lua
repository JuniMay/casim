name        = "Cyclic"
state_count = 16
color       = { 
    "#000000", "#ff44aa", "#ff3333", "#ff7744", 
    "#ffaa33", "#ffcc22", "#ffff33", "#ccff33", 
    "#99ff33", "#33ff33", "#33ffaa", "#33ffdd", 
    "#33ffff", "#33ccff", "#5599ff", "#5555ff",
}
dimensions  = 2
min_size    = { 100, 100 }

function local_evolve(x)
    sum = 0
    for i = 1, 4 do
        if (x[i] == x[5] + 1) then
            sum = sum + 1
        end
    end
    for i = 6, 9 do
        if (x[i] == x[5] + 1) then
            sum = sum + 1
        end
    end
    if (x[5] <= state_count - 2 and sum >= 1) then
        return x[5] + 1
    elseif (x[5] == state_count - 1) then
        return 0
    end
    return x[5]
end
