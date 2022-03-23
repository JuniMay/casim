name        = "Elementary Rule 90"
color       = { "#000000", "#ffffff" }
state_count = 2
dimensions  = 1
min_size    = { 100 }

function local_evolve(x)
    return (x[1] ~ x[3])
end