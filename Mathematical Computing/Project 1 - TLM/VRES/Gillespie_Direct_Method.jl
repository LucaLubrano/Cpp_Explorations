#= author: Luca Lubrano Lavadera (n11071001@qut.edu.au)
#                               School of Mathematical Sciences
#                               Science and Engineering Faculty
#                               Queensland University of Technology
=#

## Regular Gillespie Direct Method ##
"""
    Gillespie_Direct_Method(simulation_stop_time::Int=100, initial_state_vector::Vector{Int}, rate_parameters::Vector{Float64}, stoichiometric_vector::Vector{Vector{Int}}, random_seed::Int=1234)

Method 1: Generate a Gillespie Direct Method simulation based on a full set state vector

# Arguments
- `x0::Vector{Int}`: A vector of the initial state of the reaction.
- `k::Vector{Float64}`: The rate parameters k1, k2, k3 of the reaction.
- `ν::Vector{Vector{Int}}`: A vector of stoichiometric vectors v1, v2, v3.
- `a::Function`: Propensity functions of the reaction
- `R::Int`: Number of simulations to be run
- `T::Int = 100`: The simulation run time, defualts to 100.
- `projection::Bool = false`: Whether the input is a projection of the full reaction
- `species_of_interest::Int`: If projected, the species which is being observed
# Outputs
- `X` - 3 dimensional array of species data information
- `t` - time steps of data X
"""
function Gillespie_Direct_Method(x0::Vector{Int}, k::Vector{Float64}, ν::Array{Int}, 
                                    a::Function, R::Int; T::Int=100, projection::Bool=false, species_of_interest::Int=0)
    # Memory Allocation
    number_of_species::Int = length(x0[:,1])
    t = Vector{Float64}(zeros(100))
    X = Array{Int}(zeros(number_of_species, 100, R))
    t[1] = 0
    X[:,1,:] = length(x0) == number_of_species ? x0*ones(1,R) : x0
    Δt::Float64 = 0
    i::Int = 1
    length_a::Int = projection == false ? length(a(zeros(number_of_species), k)) : length(a(0, 0)) 
    probability_weighting = Vector{Float64}(zeros(length_a))
    for j in 1:R
        while (t[i] + Δt) <= T
            i += 1
            if mod(i,100) == 0
                t = vcat(t, zeros(100))
                X = hcat(X, zeros(number_of_species, 100, R))
            end
            X[:,i,j] = X[:,i-1,j]
            a0::Float64 = 0
            if !projection
                for ii in 1:length_a
                    a0 += a(X[:,i-1,j],k)[ii]
                end
                Δt = rand(Exponential(1/a0))
                for ii in 1:length_a
                    probability_weighting[ii] = a(X[:,i-1,j],k)[ii]/a0
                end
            else
                for ii in 1:length_a
                    a0 += a(X[1,i-1,j],t[i-1])[ii]
                end
                Δt = rand(Exponential(1/a0))
                if length_a == 1 
                    probability_weighting[1] = 1
                else
                    for ii in 1:length_a
                        probability_weighting[ii] = a(X[1,i,j],t[i])[ii]/a0
                    end
                end
            end
            if a0 <= 0.0
                break
            end
            jj::Int = sample(Vector{Int}(1:length_a), Weights(probability_weighting))
            X[:,i,j] += ν[jj,:]
            if projection   
                if X[1,i,j] >= 100
                    break
                end
            end

            t[i] += Δt
        end
        t = remove_zero_entries(t, 1, 100)
        X = remove_zero_entries(X, 3, 100)
        i = 1
    end
    return X,t
end
