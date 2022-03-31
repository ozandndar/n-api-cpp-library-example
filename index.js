const { hello: _hello, add: _add, getUrlsWithCallback, getUrlsWithPromise } = require('./build/Release/myLibrary');

const add = (num1, num2) => {
    return _add(num1, num2);
}

const hello = () => {
    return _hello();
}

getUrlsWithCallback('test1', (a) => {
    console.log(a)
})

const asyncWrapper = async () => {
    getUrlsWithPromise('test2').then(res => {
        console.log(res)
    })
    // console.log(_promise)
}

asyncWrapper();

console.log('finish')

module.exports = {
    hello,
    add
}