const { Octokit } = require("@octokit/rest");
const fs = require("fs");

const octokit = new Octokit({ auth: process.env.GH_TOKEN });

async function generateLeaderboard() {
  const { data } = await octokit.repos.listContributors({
    owner: "your-github-username",
    repo: "your-repository-name"
  });

  let leaderboard = "# Contribution Leaderboard\n\n";
  data.forEach((contributor, index) => {
    leaderboard += `${index + 1}. ${contributor.login} - ${contributor.contributions} contributions\n`;
  });

  fs.writeFileSync("LEADERBOARD.md", leaderboard);
}

generateLeaderboard();
