name        = "Brian's Brain 3D"
color       = { "#000000", "#ffffff", "#0000ff" }
state_count = 3
dimensions  = 3
min_size    = { 30, 30, 30 }

function local_evolve(x)
    sum = 0
    for i = 1, 27 do
        if (x[i] == 1) then
            sum = sum + 1
        end
    end
    if (x[14] == 1) then 
        sum = sum - 1
    end
    if (x[14] == 0 and sum == 2) then
        return 1
    end
    if (x[14] == 1) then
        return 2
    end
    return 0
end
