SETLOCAL ENABLEDELAYEDEXPANSION
SET counter=20
:Beginning
IF %counter% NEQ 0 (
curl -x http://10.10.15.12:3128 -d "time=3&human=driver_count&seats=4" "http://194.58.100.50/post"
SET /A counter=%counter%-1
GOTO Beginning
) ELSE (
ENDLOCAL
SET counter=
)