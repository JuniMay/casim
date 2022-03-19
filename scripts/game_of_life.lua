name          = "Conway's Game of Life"
default_color = "#ffffff"
color         = {"#000000"}
state_count   = 2;

function local_evolve(x)
    sum = 0
    for i = 1, 9 do
        sum = sum + x[i]
    end
    if (x[5] == 1) then 
        sum = sum - 1
    end
    if (x[5] == 1) then
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
