#= author: Luca Lubrano Lavadera (n11071001@qut.edu.au)
#                               School of Mathematical Sciences
#                               Science and Engineering Faculty
#                               Queensland University of Technology
=#

include("Tau_Leaping_Method.jl")

"""
# Arguments
- `k::Vector{Float64}`: Kinetic rate parameters
- `x0::Vector{Int}`: Initial state vector
- `ν::Matrix{Int}`: Stoichiometric reaction vector
- `a::Function`: Propensity function (vector ouput)
- `ϕ::Function`: Basis functions
- `Xi::Vector{Int}`: Indexation position within state vector of species of interest
- `T::Float64`: Simulation runtime used in TLM
- `τ::Float64`: The step size used in Tau Leap method
- `R::Int=5`: The number of tau leap simulations to use in linear regression

# Outputs
- `c::Matrix{Float64}`: Matrix of coefficients to be used in projected propensity functions
- `ν_proj::Matrix{Int}`: Subset matrix of stoichiometric vectors only involving species of interest
"""
function LeastSquareRegression(k::Vector{Float64}, x0::Vector{Int}, ν::Matrix{Int}, a::Function, 
                                    ϕ::Function, Xi::Vector{Int}, T::Float64, τ::Float64; R::Int=5)
    # 0. Type Initialisation
    n::Int = floor(Int, T/τ)
    X̃ = Matrix{Float64}(zeros(n, R))
    ϕ_count::Int = length(ϕ(0.0, 0.0))
    a_count = length(a(x0,k))
    ν_row_interest = Vector{Int}(zeros(size(ν)[1]))
    for i in 1:length(Xi) ν_row_interest .|= ν[:,Xi[i]] end
    Ai = [i for i in 1:a_count]
    Ai = deleteat!(Ai, ν_row_interest .== 0)
    ν_proj = Matrix{Int}(zeros(length(Ai),length(Xi)))   
    for i in 1:length(Xi)
        ν_proj[:,i] = deleteat!(ν[:,Xi[i]], ν_row_interest .== 0)
    end

    # 1. Generate Realisations of X
    X, t = Tau_Leaping_Method(x0, k, ν, τ, a, R, 0.0, T)
    X̃ = X[Xi,:,:] 

    c = Matrix{Float64}(zeros(length(Ai),ϕ_count))
    # 2. Solve Linear regression
    for j in eachindex(Ai)
        A = Matrix{Float64}(zeros(n*R, ϕ_count))
        b = Vector{Float64}(zeros(n*R))
        
        for i in 1:n 
            for ii in 1:R
                b[(i-1)*R+ii] = a(X[:,i,ii],k)[Ai[j]]
                for iii in 1:ϕ_count        
                    A[(i-1)*R+ii,iii] = ϕ(X̃[j,i,ii],t[i])[iii]
                end
            end
        end
        c[j,:] = transpose(transpose(A)*A \ transpose(A)*b)
    end

    return c, ν_proj

end

