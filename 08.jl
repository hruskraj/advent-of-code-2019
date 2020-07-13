module Day8

using Test

function getInput()
    data = readline("08.txt")
    layers = [data[i:i+149] for i in 1:150:14999]
end

numberOfChars(layer, c = '0') = count(x -> x == c, collect(layer))

@test numberOfChars("154852365962") == 0
@test numberOfChars("104802360960") == 4
@test numberOfChars("00000000") == 8

function part1()
    layers = getInput()
    minLayer = argmin(map(numberOfChars, layers))
    numberOfChars(layers[minLayer], '2') * numberOfChars(layers[minLayer], '1')
end

function getPixel(layers, pos, layerIndex = 1)
    if layers[layerIndex][pos] == '2'
        getPixel(layers, pos, layerIndex + 1)
    else
        layers[layerIndex][pos]
    end
end

@test getPixel(["002012", "221001"], 1) == '0'
@test getPixel(["002012", "221001"], 3) == '1'
@test getPixel(["002012", "221001"], 4, 2) == '0'

function part2()
    layers = getInput()
    s = collect(getPixel(layers, i) for i in 1:150)

    for i in 1:150
        print(s[i] == '1' ? 'X' : ' ')
        if i % 25 == 0
            println()
        end
    end
end


println(part1())
part2()

end
