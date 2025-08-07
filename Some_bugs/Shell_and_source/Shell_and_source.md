## Reference
- [Shell and export](../Shell_and_export/Shell_and_export.md)

## About `source`
If `export` is a method transmit a variable from `parent` to `child`, the keyword `source` is method transmit a variable from `child` to `parent`.

- Note the `source` has to assign before call `child` shell otherwise no effect. This action indicate that we are tell terminal let run this `child` shell in current terminal environment, don't create new process (not create subshell).

```bash
# example 
./parent.sh 


# Hello="?????"
# echo -e "\nwaiting child no soure"
# ./child_no_source.sh
# echo $Hello
waiting child no soure
????? # no `soure` -> `Hello` no change


# echo -e "\nwaiting child has soure"
# source ./child_has_source.sh
# echo $Hell
waiting child has soure
child has source comment # `Hello` has been changed


# echo -e "\nwaiting child no soure"
# ./child_no_source.sh
# echo $Hello
waiting child no soure
child has source comment # no `soure` -> `Hello` no change

Done :v


```