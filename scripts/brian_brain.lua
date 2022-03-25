name            = "Brian's Brain"
color           = { "#000000", "#ffffff", "#0000ff" }
state_count     = 3
dimensions      = 2
min_size        = { 100, 100 }
neighbor_radius = 1

function local_evolve(x)
    sum = 0
    for i = 1, 4 do
        if (x[i] == 1) then
            sum = sum + 1
        end
    end
    for i = 6, 9 do
        if (x[i] == 1) then
            sum = sum + 1
        end
    end
    if (x[5] == 0 and sum == 2) then
        return 1
    end
    if (x[5] == 1) then
        return 2
    end
    return 0
end
