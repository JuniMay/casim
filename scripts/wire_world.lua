name        = "Wire World"
color       = { "#000000", "#9400d3", "#ff3030", "#ffd700" }
state_count = 4
dimensions  = 2
min_size    = { 100, 100 }

function local_evolve(x)
    if x[5] == 0 then
        return 0
    end
    if x[5] == 1 then
        return 2
    end
    if x[5] == 2 then
        return 3
    end
    sum = 0
    for i = 1, 9 do
        if x[i] == 1 then
            sum = sum + 1
        end
    end
    if sum == 2 or sum == 1 then
        return 1
    else
        return 3
    end
end
