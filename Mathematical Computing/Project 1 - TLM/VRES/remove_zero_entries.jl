## Script to remove zero entries from matrix or vector

"""
Remove entries that contain zeroes from a vector or matrix

# Arguments
- `input`: Vector/Matrix to be checked
- `dimensionality': dimensions of data (1 - vector, 2 - matrix, 3 - array)
- `block_size`: size at which data is added to input

"""
function remove_zero_entries(input, dimensionality::Int, block_size::Int)
    ## Remove zero entries from data outputs
    counter::Int = 0   # number of empty entries tracker

    if dimensionality == 1
        for i in 1:block_size
            if input[end-i] == 0
                counter += 1
            else 
                break
            end
        end
        return input[1:end-counter]
    elseif dimensionality == 2 
        for i in 1:block_size
            if input[1,end-i] == 0
                counter += 1
            else 
                break
            end
        end
        return input[:,1:end-counter]
    elseif dimensionality == 3
        for i in 1:block_size
            if input[1, end-i, 1] == 0
                counter += 1
            else 
                break
            end
        end
        return input[:,1:end-counter,:]
    else 
        throw("dimensionality not accepted")
    end 
end
