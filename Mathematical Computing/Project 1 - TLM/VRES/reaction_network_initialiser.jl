#= author: Luca Lubrano Lavadera (n11071001@qut.edu.au)
#                               School of Mathematical Sciences
#                               Science and Engineering Faculty
#                               Queensland University of Technology
=#

using LinearAlgebra
using StaticArrays
"""
# Arguments
- network_name::String = BCRN to be initialised
    - allowed names: MMC, EK
- basis_functions::Bool = false, if basis functions are desired
    - projection for EK only works for X[2]
# Outputs
k, X0, v, a
"""
function reaction_network_init(network_name::String; projection::Bool=false)
    if network_name == "MMC"
        k = Vector{Float64}([1, 0.1, 0.05])
        X0 = Vector{Int}([100,0])
        ν = Matrix{Int}([1 0; -1 1; 0 -1])
        a = (X, k) -> [k[1], 
                         X[1] <= 0 ? 0 : k[2]*X[1], 
                         X[2] <= 0 ? 0 : k[3]*X[2]]
        if !projection
            return k, X0, ν, a
        else
            X0_proj = X0[2] 
            ϕ = (Xb,t) -> [1,Xb,t,Xb*t,(Xb^2)*t,Xb*(t^2),(Xb^2)*(t^2)]
            c,ν_proj = LeastSquareRegression(k, X0, ν, a, ϕ, [2], 100.0, 0.1, R=1000)
            ã = (X, t) ->  c * ϕ(X,t)
            return k, X0_proj, ν_proj, ã
        end
    elseif network_name == "EK"
        X0 = Vector{Int}([100, 100, 0, 0])
        ν = Matrix{Int}([-1 -1 1 0; 1 1 -1 0; 1 0 -1 1])
        a = (X, k) -> [(X[1] <= 0.0 || X[2] <= 0.0) ? 0.0 : k[1]*X[1]*X[2], 
                        X[3] <= 0 ? 0 : k[2]*X[3], 
                        X[3] <= 0 ? 0 : k[3]*X[3]]
        k = Vector{Float64}([0.001, 0.005, 0.01])
        if !projection
            return k, X0, ν, a
        else
            ϕ = (Xb,t) -> [1,Xb[1],t,Xb[1]*t,(Xb[1]^2)*t,Xb[1]*(t^2),(Xb[1]^2)*(t^2)]
            c,ν_proj = LeastSquareRegression(k, X0, ν, a, ϕ, [4], 250.0, 0.1, R=10000)
            # function ã(X::Float64, t::Float64)::Float64
            #     return dot(c,[1,X,t,X*t,(X^2)*t,X*(t^2),(X^2)*(t^2)])
            # end
            ã = (X, t) -> c * ϕ(X,t)   
            X0_proj = Vector([X0[4]])
            return X0_proj, ν_proj, ã
        end
    # elseif network_name == "mRNA" # DNF
    #     α_0::Int = 1
    #     α = 1000
    #     n = 2
    #     β = 5
    #     γ = 1
    #     x_0 = [0,2,0,1,0,3]
    #     ν = [1.0 -1.0 0.0  0.0  0.0  0.0 0.0  0.0 0.0  0.0 0.0  0.0; 
    #     0.0  0.0 1.0 -1.0  0.0  0.0 0.0  0.0 0.0  0.0 0.0  0.0; 
    #     0.0  0.0 0.0  0.0  1.0 -1.0 0.0  0.0 0.0  0.0 0.0  0.0; 
    #     0.0  0.0 0.0  0.0  0.0  0.0 1.0 -1.0 0.0  0.0 0.0  0.0; 
    #     0.0  0.0 0.0  0.0  0.0  0.0 0.0  0.0 1.0 -1.0 0.0  0.0;
    #     0.0  0.0 0.0  0.0  0.0  0.0 0.0  0.0 0.0  0.0 1.0 -1.0]
    #     a = (X,θ) -> [(X[6] <= 0.0) ? θ[2] + θ[1] : θ[2] + θ[1]/(1.0 + X[6]^θ[4]);
    #                     (X[1] <= 0.0) ? 0.0 : 1.0*X[1];
    #                     (X[1] <= 0.0) ? 0.0 : θ[3]*X[1];
    #                     (X[2] <= 0.0) ? 0.0 : θ[3]*X[2];
    #                     (X[2] <= 0.0) ? θ[2] + θ[1] : θ[2] + θ[1]/(1.0 + X[2]^θ[4]);
    #                     (X[3] <= 0.0) ? 0.0 : 1.0*X[3];
    #                     (X[3] <= 0.0) ? 0.0 : θ[3]*X[3];
    #                     (X[4] <= 0.0) ? 0.0 : θ[3]*X[4];
    #                     (X[4] <= 0.0) ? θ[2] + θ[1] : θ[2] + θ[1]/(1.0 + X[4]^θ[4]);
    #                     (X[5] <= 0.0) ? 0.0 : 1.0*X[5];
    #                     (X[5] <= 0.0) ? 0.0 : θ[3]*X[5];
    #                     (X[6] <= 0.0) ? 0.0 : θ[3]*X[6]]
    #     θ = [α_0, α, n, β]
    # elseif network_name == "MAPK"
    #     k1::Float64 = 0.001
    #     k2::Float64 = k1/120
    #     k3::Float64 = 0.18
    #     k4::Float64 = 0.001
    #     k5::Float64 = k4/22
    #     k6::Float64 = 0.3
    #     k7::Float64 = 0.0001
    #     k8::Float64 = k7/110
    #     k9::Float64 = 0.2
    #     k10::Float64 = 0.001
    #     k11::Float64 = k10/22
    #     k12::Float64 = 0.3
    #     θ = Vector{Float64}([k2,k3,k5,k6,k8,k9,k11,k12])
    #     bcrn.X0 = [E0;X0;0;0;P10;0;Y0;0;0;P20;0];
    #     x0 = Vector{Int}()
    #     #      1 2  3 4   5  6   7  8  9  10  11 
    #     # X = [E,X,XE,X*,P1,X*P1,Y,YX*,Y*,P2,Y*P2]
    #     ν_minus =      [1 1 0 0 0 0 0 0 0 0 0;
    #                     0 0 1 0 0 0 0 0 0 0 0;
    #                     0 0 1 0 0 0 0 0 0 0 0;
    #                     0 0 0 1 1 0 0 0 0 0 0;
    #                     0 0 0 0 0 1 0 0 0 0 0;
    #                     0 0 0 0 0 1 0 0 0 0 0;
    #                     0 0 0 1 0 0 1 0 0 0 0;
    #                     0 0 0 0 0 0 0 1 0 0 0;
    #                     0 0 0 0 0 0 0 1 0 0 0;
    #                     0 0 0 0 0 0 0 0 1 1 0;
    #                     0 0 0 0 0 0 0 0 0 0 1;
    #                     0 0 0 0 0 0 0 0 0 0 1];
    #     ν_plus =       [0 0 1 0 0 0 0 0 0 0 0;
    #                     1 1 0 0 0 0 0 0 0 0 0;
    #                     1 0 0 1 0 0 0 0 0 0 0;
    #                     0 0 0 0 0 1 0 0 0 0 0;
    #                     0 0 0 1 1 0 0 0 0 0 0;
    #                     0 1 0 0 1 0 0 0 0 0 0;
    #                     0 0 0 0 0 0 0 1 0 0 0;
    #                     0 0 0 1 0 0 1 0 0 0 0;
    #                     0 0 0 1 0 0 0 0 1 0 0;
    #                     0 0 0 0 0 0 0 0 0 0 1;
    #                     0 0 0 0 0 0 0 0 1 1 0;
    #                     0 0 0 0 0 0 1 0 0 1 0]; 
    #     ν = Matrix{Int}(ν_plus-ν_minus)
    #     a = (X,θ) -> θ.*[(X[1] < 0 || X[2] < 0) ? 0 : X[1]*X[2],
    #                       X[3] < 0 ? 0 : X[3],
    #                       X[3] < 0 ? 0 : X[3],
    #                      (X[4] < 0 || X[5] < 0) ? 0 : X[4]*X[5],
    #                       X[6] < 0 ? 0 : X[6],
    #                       X[6] < 0 ? 0 : X[6],
    #                      (X[4] < 0 || X[7] < 0) ? 0 : X[4]*X[7],
    #                       X[8] < 0 ? 0 : X[8],
    #                       X[8] < 0 ? 0 : X[8],
    #                      (X[9] < 0 || X[10] < 0) ? 0 : X[9]*X[10],
    #                       X[11] < 0 ? 0 : X[11],
    #                       X[11] < 0 ? 0 : X[11]]
    else
        throw("input not defined")
    end
end


