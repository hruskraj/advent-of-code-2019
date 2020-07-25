module Day10

using Test

function isInBounds(arr, x, y)
    return 1 ≤ x ≤ size(arr, 1) && 1 ≤ y ≤ size(arr, 2)
end

@test isInBounds([1 2; 3 4], 1, 1)
@test isInBounds([1 2; 3 4], 2, 1)
@test isInBounds([1 2; 3 4], 2, 2)
@test !isInBounds([1 2; 3 4], 1, 3)
@test !isInBounds([1 2; 3 4], -5, 0)

function numberOfVisible(data, x, y, i, j)
    if !isInBounds(data, x + i, y + j)
        0
    elseif data[x + i, y + j] == '#'
        1
    else
        numberOfVisible(data, x + i, y + j, i, j)
    end
end

@test numberOfVisible(['.' '.' '#'; '.' '.' '#'; '#' '.' '.'], 3, 1, -1, 1) == 1
@test numberOfVisible(['.' '.' '#'; '.' '.' '#'; '#' '.' '.'], 3, 1, -2, 1) == 0
@test numberOfVisible(['.' '.' '#'; '.' '.' '#'; '#' '.' '.'], 3, 1, -1, 2) == 1

function numberOfVisible(data, x, y)
    total = numberOfVisible(data, x, y, 1, 0) + numberOfVisible(data, x, y, 0, 1) + numberOfVisible(data, x, y, -1, 0) + numberOfVisible(data, x, y, 0, -1)
    for i in 1:size(data, 1), j in 1:size(data, 2)
        if gcd(i, j) == 1
            total += numberOfVisible(data, x, y, i, j) + numberOfVisible(data, x, y, i, -j) + numberOfVisible(data, x, y, -i, j) + numberOfVisible(data, x, y, -i, -j)
        end
    end
    total
end

@test numberOfVisible(['.' '.' '#'; '.' '.' '#'; '#' '.' '.'], 3, 1) == 2
testArr = ['.' '#' '.' '.' '#'
           '.' '.' '.' '.' '.'
           '#' '#' '#' '#' '#'
           '.' '.' '.' '.' '#'
           '.' '.' '.' '#' '#']
@test numberOfVisible(testArr, 5, 4) == 8

getInput() = hcat(collect(collect.(readlines("10.txt")))...)

function part1()
    data = getInput()
    results = [numberOfVisible(data, i, j) for i in 1:size(data, 1), j in 1:size(data, 2)]
    # argmax is 27, 30
    # println("argmax: ", argmax(results))
    return maximum(results)
end

println(part1())

end
