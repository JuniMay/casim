name            = "Diamon Growth"
state_count     = 7
color       = { 
    "#000000", "#0072bb", "#0067a5", "#0047ab", 
    "#0f4d92", "#000080", "#191970"
}
dimensions      = 3
min_size        = { 35, 35, 35 }
neighbor_radius = 1

function local_evolve(x)
    local sum = 0
    sum = x[5] + x[11] + x[13] + x[15] + x[17] + x[23]
    if (x[14] == 1) then
        if (sum >= 5 and sum <= 6) then
            return 1
        else 
            return 0
        end
    end
    if (x[14] == 0) then
        if ( sum >= 1 and sum <= 3) then
            return 6
        else 
            return 0
        end
    end
    return x[14] - 1
end
