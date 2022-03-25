name            = "Crystal Growth 1"
state_count     = 2
color           = { 
    "#000000", "#ffffff"
}
dimensions      = 3
min_size        = { 35, 35, 35 }
neighbor_radius = 1

function local_evolve(x)
    local sum = 0
    sum = x[5] + x[11] + x[13] + x[15] + x[17] + x[23]
    if (x[14] == 1 and sum >= 0 and sum <= 6) then
        return 1
    end
    if (x[14] == 0 and (sum == 1 or sum == 3)) then
        return 1
    end
    return 0
end
