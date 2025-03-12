#= author: Luca Lubrano Lavadera (n11071001@qut.edu.au)
#                               School of Mathematical Sciences
#                               Science and Engineering Faculty
#                               Queensland University of Technology
=#

"""
Method 1: Generate a full path Tau Leap Method simulation based on a full set state vector
# Arguments
- `x0`: The initial state vector 
- `k::Vector{Float64}`: The kinetic rate parameters
- `ν::Vector{Int}`: Matrix of reaction events 
- `τ::Float64`: Timestep incrementation
- `a::Function`: Propensity functions
- `R::Int`: Number of simulations to be performed
- `t0::Float64`: Initial time
- `T::Float64`: Final time
- `paths::Bool=true`: Whether the function will output a single timestep or the entire set of timesteps

# Outputs
- `X::Array{Float64,3}`: (length(x0) x n x R) timeseries data of reaction
- `t::Vector{Float64}`: Vector or time steps
"""
function Tau_Leaping_Method(x0, k::Vector{Float64}, ν::Array{Int}, τ::Float64, a::Function,
                                R::Int, t0::Float64, T::Float64; paths::Bool=true)
    
    # Memory Allocation
    t = Vector{Float64}([i for i in t0:τ:T])
    n = length(t) 
    species_count::Int = length(x0[:,1])
    length_a::Int = length(a(zeros(species_count), k))
    reaction_events = Array{Float64}(zeros(length_a))
    if paths
        X = Array{Float64,3}(zeros(species_count, n, R))
        X[:,1,:] = length(x0) == 4 ? x0*ones(1,R) : x0
        for i in 1:R
            for j in 1:n-1
                λ_set = Vector{Float64}(a(X[:,j,i],k).*τ)
                reaction_events = Vector{Float64}([rand(Poisson((λ <= 0 ? 0 : λ))) for λ in λ_set])
                X[:,j+1,i] = X[:,j,i] + (reaction_events' * ν)'
            end
        end
        return X,t
    else
        X = Array{Float64,3}(zeros(species_count, 2, R))
        X[:,1,:] = length(x0) == species_count ? x0*ones(1,R) : x0
        X[:,2,:] = X[:,1,:]
        for i in 1:R
            for j in 2:n
                λ_set = Vector{Float64}(a(X[:,2,i],k).*τ)
                reaction_events = [rand(Poisson((λ <= 0 ? 0 : λ))) for λ in λ_set]
                X[:,2,i] += ( reaction_events' * ν )'
            end
        end
        return X
    end
end

"""
Method 2: Generate a full path Tau Leap Method simulation based on a projected set state vector
# Arguments
- `x0`: The initial state vector 
- `ν::Vector{Int}`: Matrix of reaction events 
- `τ::Float64`: Timestep incrementation
- `a::Function`: Propensity functions
- `R::Int`: Number of simulations to be performed
- `t0::Float64`: Initial time
- `T::Float64`: Final time
- `paths::Bool=true`: Whether the function will output a single timestep or the entire set of timesteps

# Outputs
- `X::Array{Float64,3}`: (length(x0) x n x R) timeseries data of reaction
- `t::Vector{Float64}`: Vector or time steps
"""
function Tau_Leaping_Method(x0, ν::Array{Int},τ::Float64, a::Function, R::Int, t0::Float64, 
                                T::Float64; paths::Bool=true)

    t = Vector{Float64}([i for i in t0:τ:T])
    n = length(t) 
    # species_count::Int = length(x0)
    if paths
        X = Array{Float64,3}(zeros(1, n, R))
        X[:,1,:] .= x0
        for i in 1:R
            for j in 1:n-1
                λ_set = Vector{Float64}(a(X[:,j,i],t[j]).*τ)
                reaction_events = [rand(Poisson((λ <= 0 ? 0 : λ))) for λ in λ_set]
                X[:,j+1,i] = X[:,j,i] + ( reaction_events' * ν )' 

                # The below line computes line 87,88,89 much quicker, however, is quite a bit less readable
                #   as well as being less general, allowing only 1D observable species
                # X[:,j+1,i] = X[:,j,i] + ( [rand(Poisson((λ <= 0 ? 0 : λ))) for λ in a(X[1,j,i],t[j])*τ] * ν[1] ) 
            end
        end    
        return X,t         
    else
        X = Array{Float64,3}(zeros(1, 2, R))
        X[:,1,:] .= x0
        X[:,2,:] = X[:,1,:]
        for i in 1:R
            for j in 2:n
                λ_set = Vector{Float64}(a(X[:,2,i],t[j]).*τ)
                reaction_events = [rand(Poisson((λ <= 0 ? 0 : λ))) for λ in λ_set]
                X[:,2,i] += ( reaction_events' * ν )'                 
            end
        end   
        return X       
    end
end

"""
Method 3: Generate a full path Tau Leap Method simulation based on a full set state vector with noise
# Arguments
- `x0`: The initial state vector 
- `k::Vector{Float64}`: The kinetic rate parameters
- `ν::Vector{Int}`: Matrix of reaction events 
- `τ::Float64`: Timestep incrementation
- `a::Function`: Propensity functions
- `g::Function`: Noise function
- `t::Vector{Float64}`: Vector of observation times

# Outputs
- `X::Array{Float64,3}`: (length(x0) x n x R) timeseries data of reaction
- `t::Vector{Float64}`: Vector or time steps
"""
function Tau_Leaping_Method(x0, k::Vector{Float64}, ν::Array{Int}, τ::Float64, a::Function, 
                                g::Function, t::Vector{Float64})
                                
    n = length(t)
    Xs = x0
    # Memory Allocation
    number_of_species::Int = length(x0)
    Y = Matrix{Float64}(zeros(number_of_species,n))
    Y[:,1] = g(x0)
    for i in 2:n
        X, = Tau_Leaping_Method(Xs, k, ν, τ, a, 1, t[i-1], t[i])
        Y[:,i] = g(X[:,end,1])
        Xs = X[:,end,1]
    end
    return Y
end

"""
Method 4: Generate a full path Tau Leap Method simulation based on a full set state vector with noise
# Arguments
- `x0`: The initial state vector 
- `ν::Vector{Int}`: Matrix of reaction events 
- `τ::Float64`: Timestep incrementation
- `a::Function`: Propensity functions
- `g::Function`: Noise function
- `t::Vector{Float64}`: Vector of observation times

# Outputs
- `X::Array{Float64,3}`: (length(x0) x n x R) timeseries data of reaction
- `t::Vector{Float64}`: Vector or time steps
"""
function Tau_Leaping_Method(x0, ν::Array{Int}, τ::Float64, a::Function, g::Function, t::Vector{Float64})
    # Memory Allocation
    n = length(t)
    Y = Matrix{Float64}(zeros(length(x0), n))
    Xs = x0
    Y[:,1] = g(x0)
    for i in 2:n
        X, = Tau_Leaping_Method(Xs, ν, τ, a, 1, t[i-1], t[i])
        Y[:,i] = g(X[:,end,1])
        Xs = X[:,end,1]
    end
    return Y
end
