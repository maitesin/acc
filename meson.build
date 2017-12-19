project('ACC', 'c')
# Includes
core_inc = include_directories('inc/fff', 'inc/unity', 'src')
# Test for the lexer
lexer_tests = executable('lexer_tests', 'unittest/lexer_test.c', 'inc/unity/unity.c', 'src/token.c', 'src/lexer.c', include_directories : core_inc)
test('Lexer', lexer_tests)
# Test for the grammar
grammar_tests = executable('grammar_tests', 'unittest/grammar_test.c', 'src/token.c', 'src/ast.c', 'src/grammar.c', include_directories : core_inc)
test('Grammar', grammar_tests)
# Executable of ARM C Compiler
executable('acc', 'src/acc.c', 'src/token.c', 'src/lexer.c', 'src/ast.c', 'src/grammar.c', 'src/generator.c', include_directories : core_inc)
