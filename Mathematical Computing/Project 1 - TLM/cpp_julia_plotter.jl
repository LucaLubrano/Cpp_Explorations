include("/Users/luca/Documents/Github/Cpp_Explorations/Mathematical Computing/Project 1 - TLM/VRES/VRES.jl")
using .VRES
using PyPlot
using CSV
using DataFrames
using Random
using BenchmarkTools

population_a = CSV.read("mmc_tau_leap_data_v3.csv", values; select = [1], header = false) |> only
population_b = CSV.read("mmc_tau_leap_data_v3.csv", values; select = [2], header = false) |> only
t = CSV.read("mmc_tau_leap_data_v3.csv", values; select = [3], header = false) |> only
k, x0, ν, a = reaction_network_init("MMC")
τ = 1.0
Data1, time = @btime Tau_Leaping_Method(x0, k, ν, τ, a, 1, 0.0, 100.0)
w = 7.143*0.394*8 # with inches
h = 5.001*0.394*6 # height inches
h = figure(figsize=(w/2,(h-0.7)/2))
plot(t, population_a, color = "#073b4c", alpha = 0.6)
plot(t, population_b, color = "#118ab2", alpha = 0.6)
plot(time, Data1[1,:,1], color = "#ef476f", alpha = 0.6, linestyle = "--")
plot(time, Data1[2,:,1], color = "#ef476f", alpha = 0.6, linestyle = "--")
title("Michelis Menton Simulation")
xlabel("Time",fontsize=16)
ylabel("Copy Number (Population)",fontsize=16)
legend(["Species A", "Species B"],fontsize=16)
h.set_tight_layout(true)
display(h)