name            = "Clouds 1"
state_count     = 2
color           = { 
    "#000000", "#ffffff"
}
dimensions      = 3
min_size        = { 35, 35, 35 }
neighbor_radius = 1

function local_evolve(x)
    local sum = 0
    for i = 1, 13 do
        if (x[i] ~= 0) then
            sum = sum + 1
        end
    end
    for i = 15, 27 do
        if (x[i] ~= 0) then
            sum = sum + 1
        end
    end
    if (x[14] == 1 and sum >= 13 and sum <= 26) then
        return 1
    end
    if (x[14] == 0 and sum >= 13 and sum <= 19 and sum ~= 15 and sum ~=16) then
        return 1
    end
    return 0
end
