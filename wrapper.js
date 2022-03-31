const { hello: _hello, add: _add, getUrlsWithCallback, getUrlsWithPromise } = require('./build/Release/myLibrary');

const add = (num1, num2) => {
    return _add(num1, num2);
}

const hello = () => {
    return _hello();
}

const callback = (a) => {
    console.log(a);
}

getUrlsWithCallback('test1', callback);

const asyncWrapper = async () => {
    const res = await getUrlsWithPromise('test2');
    console.log(res);
}

asyncWrapper();

module.exports = {
    hello,
    add
}