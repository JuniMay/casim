name        = "Brian's Brain"
color       = { "#000000", "#9400d3", "#ff3030", "#ffd700" }
state_count = 4
dimensions  = 2
min_size    = { 100, 100 }

function local_evolve(x)
    local cnt = { 0, 0, 0, 0 }
    for i = 1, 4 do
        cnt[x[i] + 1] = cnt[x[i] + 1] + 1
    end
    for i = 6, 9 do
        cnt[x[i] + 1] = cnt[x[i] + 1] + 1
    end
    if (x[5] == 0) then
        if (cnt[4] == 3 and cnt[2] == 1) then
            return 1
        end
        if (cnt[2] == 2) then
            return 1
        end
    else
        if (x[5] == 1) then
            return 2
        end
        if (x[5] == 2) then
            return 0
        end
    end
    return 3
end
