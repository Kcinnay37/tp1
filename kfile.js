let project = new Project('tp1');

project.kore = false;
project.cmd = true;

project.addFile('Sources/**');
project.setDebugDir('./Deployment');

resolve(project);