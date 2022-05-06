export function Execute_script(...props) {
  const { cp } = require("child_process");
  cp.spawn("sh ../../script_exemple.sh", props, (error, stdout, stderr) => {
    console.log(stdout);
    console.log(stderr);
    if (error !== null) {
      console.log(`exec error: ${error}`);
    }
  });
}
