name        = "Elementary Rule 30"
color       = { "#ffffff", "#000000" }
state_count = 2
dimensions  = 1
min_size    = { 100 }

function local_evolve(x)
    return (x[1] ~ (x[2] | x[3]))
end