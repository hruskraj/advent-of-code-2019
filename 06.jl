module Day6

using DataStructures, Test

function readInput()
    data = DefaultDict{String, Vector{String}}(Vector{String})

    for row in readlines("06.txt")
        (key, val) = split(row, ")")
        push!(data[key], val)
    end
    data
end

function readInputReversed()
    data = Dict{String, String}()

    for row in readlines("06.txt")
        (val, key) = split(row, ")")
        push!(data, (key => val))
    end
    data
end

function getTotal(data, object::String, dist::Int)
    if isempty(data[object])
        dist
    else
        x = 0
        for other in data[object]
            x += getTotal(data, other, dist + 1)
        end
        x + dist
    end
end

@test getTotal(Dict("COM" => ["B"], "B" => []), "COM", 0) == 1
@test getTotal(Dict("COM" => ["B"], "B" => ["C" "G"],
                    "G" => ["H"], "C" => ["D"], "D" => [],
                     "G" => []), "COM", 0) == 8

function part1()
    data = readInput()
    getTotal(data, "COM", 0)
end

function getPath(data, object::String)
    res = Vector{String}()
    x = object
    while data[x] != "COM"
        push!(res, data[x])
        x = data[x]
    end
    reverse(res)
end

@test getPath(Dict("I" => "D", "D" => "C", "C" => "B",
                   "B" => "COM", "H" => "G", "G" => "B"), "I") == ["B", "C", "D"]

function part2()
    data = readInputReversed()
    p₁ = getPath(data, "SAN")
    p₂ = getPath(data, "YOU")

    i = 1
    while p₁[i] == p₂[i]
        i += 1
    end
    length(p₁) + length(p₂) - 2i + 2
end


println(part1())
println(part2())

end
