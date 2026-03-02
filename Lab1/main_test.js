const test = require('node:test');
const assert = require('assert');
const { MyClass, Student } = require('./main');

test("Test MyClass's addStudent", () => {
    const myClass = new MyClass();

    const student1 = new Student();
    student1.setName('Alice');

    // 正常加入學生
    const id1 = myClass.addStudent(student1);
    assert.strictEqual(id1, 0);

    // 非 Student 物件加入
    const id2 = myClass.addStudent({ name: 'Fake' });
    assert.strictEqual(id2, -1);
});

test("Test MyClass's getStudentById", () => {
    const myClass = new MyClass();
    const student = new Student();
    student.setName('Bob');
    const id = myClass.addStudent(student);

    // 正確索引
    const result = myClass.getStudentById(id);
    assert.strictEqual(result.getName(), 'Bob');

    // 無效索引
    assert.strictEqual(myClass.getStudentById(-1), null);
    assert.strictEqual(myClass.getStudentById(999), null);
});

test("Test Student's setName", () => {
    const student = new Student();

    // 設定合法字串
    student.setName('Charlie');
    assert.strictEqual(student.name, 'Charlie');

    // 設定非字串不影響 name
    student.setName(123);
    assert.strictEqual(student.name, 'Charlie');
});

test("Test Student's getName", () => {
    const student = new Student();

    // 未設定名字
    assert.strictEqual(student.getName(), '');

    // 設定名字後取得
    student.setName('Daisy');
    assert.strictEqual(student.getName(), 'Daisy');
});
